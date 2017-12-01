#include "rpn.h"

int main(void) {
	WDTCTL  = WDTPW | WDTHOLD;                // Disable Watchdog
	BCSCTL1 = CALBC1_1MHZ;                    // Run @ 1MHz
	DCOCTL  = CALDCO_1MHZ;

	serial_init(9600);                        // Initialize Serial Comms

	int stack[4] = { 0 };
	int cursor = 0;

	for (;;) {
		int j = 0;                            // Char array counter
		char line[32] = { 0 };                // Init empty array

		cio_print((char *) "$ ");             // Display prompt
		char c = cio_getc();                  // Wait for a character

		while(c != '\r') {                    // until return sent then ...
			if(c == 0x08) {                   //  was it the delete key?
				if(j != 0) {                  //  cursor NOT at start?
					line[--j] = 0;            //  delete key logic
					cio_printc(0x08); cio_printc(' '); cio_printc(0x08);
				}
			} else {                          // otherwise ...
				line[j++] = c; cio_printc(c); //  echo received char
			}

			c = cio_getc();                   // Wait for another
		}

		char *token, *p = line;

		cio_print("\n\r");
		while ((token = strsep(&p, " ")) != NULL) {
			if (strchr("+-*/^%", token[0]) && token[1] == 0) {
				if (cursor < 2) {
					cio_print("! NOT ENOUGH ITEMS ON STACK\n\r");
				} else {
					int a = stack[--cursor];
					stack[cursor] = 0;
					int b = stack[--cursor];

					switch (token[0]) {
						case '+':
							stack[cursor++] = add(a, b);
							break;
						case '-':
							stack[cursor++] = sub(a, b);
							break;
						case '/':
							stack[cursor++] = divd(a, b);
							break;
						case '*':
							stack[cursor++] = mul(a, b);
							break;
						case '^':
							stack[cursor++] = powr(a, b);
							break;
						case '%':
							stack[cursor++] = mod(a, b);
							break;
						default:
							cio_print("! UNKNOWN OPERATION\n\r");
							break;
					}
				}
			} else {
				if (cursor == 4) {
					cio_print("! STACK FULL\n\r");
					break;
				} else {
					stack[cursor++] = atoi(token);
				}
			}
		}

		cio_print("\n\r");
		for (int i = 0; i < 4; i++) {
			if (i < cursor) {
				cio_printf("%i: %i\n\r", i, stack[i]);
			} else {
				cio_printf("%i: -\n\r", i);
			}
		}
		cio_print("\n\r");
	}

	return 0;
}
