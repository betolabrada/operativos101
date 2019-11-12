#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void write_func(char *wordToFind, char *replacement, int tmp, char *buffer) {
  if (strcmp(wordToFind, buffer) == 0) {
    write(tmp, replacement, strlen(replacement));
    write(tmp, " ", 1);
    printf("Se reemplazo %s con %s\n", wordToFind, replacement);
  } else {
    write(tmp, buffer, strlen(buffer));
    write(tmp, " ", 1);
  }
}
int main(int argc, char **argv) {
  char *file = argv[1];
  char *wordToFind = argv[2];
  char *replacement = argv[3];
  char tmpFile[] = "/tmp.txt";

  char *pwd = getcwd(NULL, 0);
  char path[strlen(file) + strlen(pwd) + 2]; // por / y null char '\0'
  char tmp_path[strlen(tmpFile) + strlen(pwd) + 2];
  sprintf(path, "%s/%s", pwd, file);
  sprintf(tmp_path, "%s%s", pwd, tmpFile);

  printf("pwd %s\n", path);
  printf("pwd %s\n", tmp_path);

  int fd = open(path, O_RDONLY);
  int tmp = open(tmp_path, O_WRONLY | O_CREAT, 0666);

  char buffer[100];
  char c;
  int i = 0;
  while (read(fd, &c, 1)) {
    if (c != ' ') {
      buffer[i++] = c;
    }

    else {
      buffer[i] = '\0';
      i = 0;
      write_func(wordToFind, replacement, tmp, buffer);
    }
  }
  buffer[i] = '\0';
  write_func(wordToFind, replacement, tmp, buffer);

  close(fd);
  close(tmp);
  unlink(path);
  link(tmp_path, path);
  unlink(tmp_path);

  return 0;
}