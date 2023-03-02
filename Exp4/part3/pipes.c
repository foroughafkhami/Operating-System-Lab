#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 128
#define READ_END 0
#define WRITE_END 1
void convert_str(char s[], char cs[]) {
  int i;
  for(i = 0; s[i] != '\0'; i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      cs[i] = s[i] - 32;
    } else if (s[i] >= 'A' && s[i] <= 'Z') {
      cs[i] = s[i] + 32;
    } else {
      cs[i] = s[i];
    }
  }
  cs[i] = '\0';
}

int main(void) {
  char write_msg_pr[BUFFER_SIZE] = "This Is First Process.";
  char read_msg_pr[BUFFER_SIZE], write_msg_ch[BUFFER_SIZE], read_msg_ch[BUFFER_SIZE];

  int fd_pr[2], fd_ch[2];
  pid_t pid;

  if (pipe(fd_pr) == -1) {
    printf("Parent pipe creation failed!");
    return 1;
  }

  if (pipe(fd_ch) == -1) {
    printf("Child pipe creation failed!");
    return 1;
  }

  pid = fork();
  

  if(pid < 0) { // ERROR
    printf("Fork failed!");
    return 1;
  }

  if (pid > 0) {  // Parent process
    // close unwanted pipe ends by parent
    close(fd_pr[READ_END]);
    close(fd_ch[WRITE_END]);
    
    // write to parent pipe FOR child to read
    write(fd_pr[WRITE_END], write_msg_pr, strlen(write_msg_pr) + 1);
    printf("write to parent pipe FOR child to read: %s\n", write_msg_pr);
    
    // read from child pipe
    read(fd_ch[READ_END], read_msg_pr, BUFFER_SIZE);
    printf("Parent read: %s\n", read_msg_pr);

    close(fd_pr[WRITE_END]);
    close(fd_ch[READ_END]);
    
  } else {  // Child process
  
    close(fd_ch[READ_END]);
    close(fd_pr[WRITE_END]);
    
    // read from parent pipe
    read(fd_pr[READ_END], read_msg_ch, BUFFER_SIZE);
    printf("Child read: %s\n", read_msg_ch);
    
    //convert the string
    convert_str(read_msg_ch, write_msg_ch);
    
    //write to child pipe the converted message
    write(fd_ch[WRITE_END], write_msg_ch, strlen(write_msg_ch) + 1);
    printf("write to child pipe the converted message: %s\n", write_msg_ch);
    
    close(fd_ch[WRITE_END]);
    close(fd_pr[READ_END]);
  }
}
  


