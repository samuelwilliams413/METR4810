/*
timer_init() has to be called before calling any one of the functions below
*/
void timer_init(void);

/*
Return the clock_ticks of timer 2
*/
uint32_t get_clock_ticks(void);

/*
Delay in milliseconds
*/
void mil_delay(int milliseconds);

