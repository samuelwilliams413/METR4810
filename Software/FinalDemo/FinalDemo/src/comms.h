/*
Initialize asynchronous serial communication
*/
extern void uart_init(void);

/*sent_str() sends a string from the microcontroller through serial
bluetooth communication
*/
extern void send_str(char msg[]);

/*
receive one character through bluetooth serial communication
*/

extern uint8_t get_char(void);

/*
sen_confirmation_msg() is used to test the communication
*/
extern void send_confirmation_msg(uint8_t data);
