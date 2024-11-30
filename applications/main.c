/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-25     RT-Thread    first version
 */

#include <rtthread.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
static rt_thread_t rt1 =RT_NULL;//rt1为线程TCB 的返回值 若创建失败则返回RT_NULL
static rt_thread_t rt2 = RT_NULL;
static rt_timer_t timer1;
static rt_timer_t timer2;
rt_sem_t rt_sem_init();
int timer1_sec=0;

static void time1out(void *paramter)
{
    timer1_sec++;
    if (timer1_sec==60) {
        rt_kprintf("have been 1 minutes");
        timer1_sec=0;
    }
}
static void timer2out(void *paramter)
{

    rt_kprintf("timer2 running only once");

}
void thread1_entry(void *parameter)//创建任务本体 void *parameter必须和api中保持一致!!!
{
    int count = 0;
    while(1)
    {
        rt_kprintf("Thread_1 is running,count=%d\r\n",count);
        count++;
        rt_thread_mdelay(10000);
    }
}
void thread2_entry(void *parameter)
{
    while(1)
    {
        rt_kprintf("Thread2 Running cause high priority\r\n");
        rt_thread_mdelay(10000);
    }

}
int main(void)
{
    GPIO
    rt1 = rt_thread_create("Thread1", thread1_entry, RT_NULL, 1024, 20, 10);//创建任务线程,并用rt1接收创建现成的返回值
    rt2 = rt_thread_create("thread2", thread2_entry, RT_NULL, 1024, 30, 10);
    timer1 =  rt_timer_create("Timer1", time1out, RT_NULL, 1000, RT_TIMER_FLAG_PERIODIC);
    timer2 =  rt_timer_create("Timer2", timer2out, RT_NULL, 1000, RT_TIMER_FLAG_ONE_SHOT);
    if (rt1!=RT_NULL)//若创建成功则将任务激活!
    {
        rt_thread_startup(rt1);
    }
    if (rt2!=RT_NULL)//若创建成功则将任务激活!
        {
            rt_thread_startup(rt2);
        }
    if (timer1!=RT_NULL) {
        rt_timer_start(timer1);
    }
    rt_timer_start(timer2);
    return RT_EOK;
}
