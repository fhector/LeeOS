typedef void (*init_func)(void);

#define UFCON0  ((volatile unsigned int *)(0x50000020))

void helloworld(void)
{
    const char *p="helloworld\n";
    while(*p)
    {
        *UFCON0=*p++;
    };
}

void test_mmu(void)
{
    const char *p="test_mmu\n";
    while(*p)
    {
        *(volatile unsigned int *)0xd0000020=*p++;
    };
}

static init_func init[]=
{
    helloworld,
    0,
};

void timer_init(void)
{
#define TIMER_BASE  (0xd1000000)
#define TCFG0   ((volatile unsigned int *)(TIMER_BASE+0x0))
#define TCFG1   ((volatile unsigned int *)(TIMER_BASE+0x4))
#define TCON    ((volatile unsigned int *)(TIMER_BASE+0x8))
#define TCONB4  ((volatile unsigned int *)(TIMER_BASE+0x3c))
    *TCFG0|=0x800;
    *TCON&=(~(7<<20));
    *TCON|=(1<<22);
    *TCON|=(1<<21);

    *TCONB4=10000;

    *TCON|=(1<<20);
    *TCON&=~(1<<21);

    umask_int(14);
    enable_irq();
}



void *kmalloc(unsigned int size);
void plat_boot(void)
{
    int i;
    for(i=0; init[i]; i++)
    {
        init[i]();
    }
    init_sys_mmu();
    start_mmu();
    test_mmu();
    test_printk();
//  timer_init();
    init_page_map();
    kmalloc_init();
    char *p1,*p2,*p3,*p4;
    p1=kmalloc(127);
    printk("the first alloced address is %x\n",p1);
    p2=kmalloc(124);
    printk("the second alloced address is %x\n",p2);
    kfree(p1);
    kfree(p2);
    p3=kmalloc(119);
    printk("the third alloced address is %x\n",p3);
    p4=kmalloc(512);
    printk("the forth alloced address is %x\n",p4);
    while(1);
}
