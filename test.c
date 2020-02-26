int sum(int a, int b) {
    int sum = 0;
    goto cond;
loop:
    sum += a;
    a++;
cond:
    if (a <= b) {
        goto loop;
    }
    return sum;
}

int main() {
    return sum(2, 4);
}
