#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    long long x, y;
} Point;

Point points[100001];
int base_index;

double cross_product(Point a, Point b, Point c) {
    //[(b - a), (c - a)]
    long long bx = b.x - a.x;
    long long by = b.y - a.y;
    long long cx = c.x - a.x;
    long long cy = c.y - a.y;
    return (double)bx * cy - (double)by * cx;
}

double distance(Point a, Point b) {
    long long dx = b.x - a.x;
    long long dy = b.y - a.y;
    return sqrt((double)dx * dx + (double)dy * dy);
}

int compare(const void *a, const void *b) {
    Point p1 = *(Point *)a;
    Point p2 = *(Point *)b;
    Point base = points[base_index];

    double cp = cross_product(base, p1, p2);
    if (fabs(cp) < 1e-9) {//проврека коллинеарности
        return distance(base, p1) < distance(base, p2) ? -1 : 1;
    }
    return cp > 0 ? -1 : 1;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) {
        printf("bad number of lines\n");
        return 0;
    }

    if (N < 0 || N > 100000) {
        printf("bad number of points\n");
        return 0;
    }

    if (N == 0) {
        return 0;
    }

    for (int i = 0; i < N; i++) {
        if (scanf("%lld %lld", &points[i].x, &points[i].y) != 2) {
            printf("bad number of lines\n");
            return 0;
        }
    }

    base_index = 0;
    for (int i = 1; i < N; i++) {
        if (points[i].y < points[base_index].y ||
            (points[i].y == points[base_index].y && points[i].x < points[base_index].x)) {
            base_index = i;
        }
    }

    Point temp = points[0];
    points[0] = points[base_index];
    points[base_index] = temp;
    base_index = 0;

    qsort(points + 1, N - 1, sizeof(Point), compare);

    Point stack[100001];
    int stack_size = 0;

    stack[stack_size++] = points[0];
    if (N > 1) {
        stack[stack_size++] = points[1];
    }

    for (int i = 2; i < N; i++) {//удаленение внутренних точек
        while (stack_size >= 2 && cross_product(stack[stack_size - 2], stack[stack_size - 1], points[i]) <= 0) {
            stack_size--;
        }
        stack[stack_size++] = points[i];
    }

    if (stack_size >= 3) {
        // доп проверка последней точки
        while (stack_size >= 3 && cross_product(stack[0], stack[stack_size - 1], stack[stack_size - 2]) == 0) {
            stack_size--;
        }
    }

    for (int i = 0; i < stack_size; i++) {
        printf("%lld %lld\n", stack[i].x, stack[i].y);
    }

    return 0;
}
