/********************************************************************************* @file    uart_atmel.h* @date    23032017* @brief   Atmel example UART code********************************************************************************     EXTERNAL FUNCTIONS******************************************************************************* uart_init() – intialise atmel uart* uart_getchar() – get first char waiting in ring buffer* uart_char_waiting() – check if char is waiting in ring buffer* uart_putchar() – send data via uart*******************************************************************************/
/* External function prototypes ----------------------------------------------*/
extern void uart_init(void);
extern uint8_t uart_getchar(void);
extern bool uart_char_waiting(void);
extern void uart_putchar(uint8_t data);