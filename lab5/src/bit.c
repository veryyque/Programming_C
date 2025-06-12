#include "bit.h"

void init_bit_write(bit_write *bw, FILE *out)
{
    bw->out = out;
    bw->current = 0;
    bw->bit_position = 0;
}

void WriteBit(bit_write *bw, int bit_value)
{
    if (bw->bit_position == 8)
    {
        fwrite(&bw->current, 1, 1, bw->out);
        bw->current = 0;
        bw->bit_position = 0;
    }
    if (bit_value)
        bw->current |= (1 << (7 - bw->bit_position));
    bw->bit_position++;
}

void WriteBits(bit_write *bw, byte sym)
{
    for (int i = 7; i >= 0; --i)
    {
        WriteBit(bw, (sym >> i) & 1);
    }
}

void flush_bit_write(bit_write *bw)
{
    if (bw->bit_position > 0)
    {
        fwrite(&bw->current, 1, 1, bw->out);
        bw->current = 0;
        bw->bit_position = 0;
    }
}

void serializeTree(const huffman_node *node, bit_write *bw)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        WriteBit(bw, 0);
        WriteBits(bw, node->symbol);
    }
    else
    {
        WriteBit(bw, 1);
        serializeTree(node->left, bw);
        serializeTree(node->right, bw);
    }
}

void init_bit_read(bit_read *br, FILE *in)
{
    br->in = in;
    br->current = 0;
    br->bit_position = 8;
}

int ReadBit(bit_read *br)
{
    if (br->bit_position == 8)
    {
        if (fread(&br->current, 1, 1, br->in) != 1)
            return -1;
        br->bit_position = 0;
    }
    int bit_value = (br->current >> (7 - br->bit_position)) & 1;
    br->bit_position++;
    return bit_value;
}

byte ReadBits(bit_read *br)
{
    byte sym = 0;
    for (int i = 0; i < 8; ++i)
    {
        int bit = ReadBit(br);
        if (bit == -1)
            break;
        sym = (sym << 1) | bit;
    }
    return sym;
}

huffman_node *deserializeTree(bit_read *br)
{
    int bit = ReadBit(br);
    if (bit == -1)
        return NULL;
    if (bit == 0)
    {
        byte sym = ReadBits(br);
        return make_leaf(sym, 0);
    }
    huffman_node *left = deserializeTree(br);
    if (!left)
        return NULL;
    huffman_node *right = deserializeTree(br);
    if (!right)
    {
        destroy_tree(left);
        return NULL;
    }
    return make_inner_node(left, right);
}

