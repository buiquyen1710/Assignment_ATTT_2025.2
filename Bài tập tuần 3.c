#include <stdio.h>
#include <stdint.h>

#define MOD 0x409   // x^10 + x^3 + 1 = 10000001001b = 0x409

// tim bac cua da thuc
int degree(uint16_t a)
{
    for(int i=15;i>=0;i--)
        if(a & (1<<i)) return i;
    return -1;
}

// in da thuc dang nhi phan
void print_poly(uint16_t a)
{
    int d = degree(a);
    for(int i=d;i>=0;i--)
        printf("%d",(a>>i)&1);
}

// phep chia da thuc trong truong GF(2)
void poly_div(uint16_t a,uint16_t b,uint16_t *q,uint16_t *r)
{
    *q=0;
    *r=a;

    int db = degree(b);

    while(degree(*r) >= db)
    {
        int shift = degree(*r) - db;
        *q ^= (1<<shift);
        *r ^= (b<<shift);
    }
}

// nhan da thuc trong truong GF(2)
uint32_t poly_mul(uint16_t a,uint16_t b)
{
    uint32_t res=0;

    while(b)
    {
        if(b&1) res ^= a;
        a <<=1;
        b >>=1;
    }

    return res;
}

// mod theo m(x)
uint16_t poly_mod(uint32_t a)
{
    while(degree(a) >= 10)
    {
        int shift = degree(a) - 10;
        a ^= ((uint32_t)MOD << shift);
    }

    return (uint16_t)a;
}

// Euclid mo rong
uint16_t gf_inverse(uint16_t a)
{
    uint16_t r0 = MOD;
    uint16_t r1 = a;

    uint16_t t0 = 0;
    uint16_t t1 = 1;

    printf("Step | r0 | r1 | q | r | t\n");

    while(r1 != 0)
    {
        uint16_t q,r;

        poly_div(r0,r1,&q,&r);

        uint16_t temp = t0 ^ poly_mod(poly_mul(q,t1));

        printf("---------------------------------\n");
        printf("r0 = "); print_poly(r0); printf("\n");
        printf("r1 = "); print_poly(r1); printf("\n");
        printf("q  = "); print_poly(q);  printf("\n");
        printf("r  = "); print_poly(r);  printf("\n");

        r0 = r1;
        r1 = r;

        t0 = t1;
        t1 = temp;
    }

    return t0;
}

int main()
{
    uint16_t a = 523;
    uint16_t b = 1015;

    printf("Inverse of a=523\n");
    uint16_t ainv = gf_inverse(a);

    printf("\na^-1 = %d\n",ainv);

    printf("\nInverse of b=1015\n");
    uint16_t binv = gf_inverse(b);

    printf("\nb^-1 = %d\n",binv);

    return 0;
}