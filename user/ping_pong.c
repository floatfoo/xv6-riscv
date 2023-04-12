#include "user.h"

/* Excersice 1.6
 * Ping pong
 */

// TODO: time in exchange per second

int
main() {
  int ping[2], pong[2];

  pipe(ping);
  pipe(pong);

  if (fork()) {
    // parent process
    // const time_t start_time = time(NULL);

    close(ping[0]);
    close(pong[1]);
    
    char recv_buf[8];
    for (int i = 0; i < 100; ++i) {
      write(ping[1], "Ping!\n", 6);
      read(pong[0], recv_buf, 8);
      write(1, recv_buf, 8);
    }
    
    close(ping[1]);
    close(pong[0]);
  } else {
    /* child process
     * reads ping and prints it
     * writes pong
     */
    close(ping[1]);
    close(pong[0]);

    char recv_buf[8];
    for (int i = 0; i < 100; ++i) {
      read(ping[0], recv_buf, 8);
      write(1, recv_buf, 8);
      write(pong[1], "Pong!\n", 6);
    }
    
    close(ping[0]);
    close(pong[1]);
  }

  return 0;
}
