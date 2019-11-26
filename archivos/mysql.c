

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
typedef struct s {
  char firstName[20];
  char lastName[20];
  int studentID;
  char semester;
} Student;

int writeStudent(int argc, char **argv) {
  char *fileName = argv[1];

  int fd = open(fileName, O_WRONLY | O_CREAT, 0666);

  Student studentWithLN;
  for (int i = 0; i < 10; i++) {
    Student myStudent;
    myStudent.studentID = (i + 1) * 10;
    myStudent.semester = i + 1;
    sprintf(myStudent.firstName, "juanito_%d", i);
    sprintf(myStudent.lastName, "perez_%d", i);
    write(fd, &myStudent, sizeof(myStudent));
  }
  close(fd);
  Student myStudent;

  return 0;
}

int readStudent(int argc, char **argv) {
  char *fileName = argv[1];

  int fd = open(fileName, O_RDONLY);
  Student myStudent;
  while (read(fd, &myStudent, sizeof(myStudent))) {
    printf("%s %s: %d: %d\n", myStudent.firstName, myStudent.lastName,
           myStudent.studentID, myStudent.semester);
  }
  close(fd);
  return 0;
}

int main(int argc, char **argv) {
  char *fileName = argv[1];
  char *lastName = argv[2];
  char *newLastName = argv[3];
  int i = -1;
  int recordPos = -1;

  int fd = open(fileName, O_RDONLY);
  Student myStudent;

  while (read(fd, &myStudent, sizeof(myStudent))) {
      i++;
      if (!strcmp(myStudent.lastName, lastName)){
          recordPos = i;
          break;
      }
  }

  close(fd);

  if(recordPos != -1) {
      printf("El record existe en la posicion %d\n", recordPos);
      char lastNameBuf[sizeof(myStudent.lastName)];
      strncpy(lastNameBuf, newLastName, sizeof(myStudent.lastName));
      fd = open(fileName, O_WRONLY);
      lseek(fd, recordPos*sizeof(myStudent) + sizeof(myStudent.firstName), SEEK_SET);
      write(fd, &lastNameBuf, sizeof(myStudent.lastName));
      close(fd);
  }
  else {
      printf("El record no existe\n");
  }
  return 0;
  
}