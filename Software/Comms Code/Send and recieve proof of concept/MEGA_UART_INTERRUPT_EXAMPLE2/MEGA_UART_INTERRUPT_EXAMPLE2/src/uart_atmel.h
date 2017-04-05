/**
/* External function prototypes ----------------------------------------------*/
extern void uart_init(void);
extern uint8_t uart_getchar(void);
extern bool uart_char_waiting(void);
extern void uart_putchar(uint8_t data);