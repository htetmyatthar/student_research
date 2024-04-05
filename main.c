#include "utils.h"

#define IT 0
#define LAW 1
#define ENVIRONMENT 2
#define ARTS 3
#define FOREIGN_LANGUAGES 4
#define BA 5
#define LIBRARY 6

const int MINIMUM_COMMITTEE_MEMBER_COUNT = 3;

int main(void) {
  // one constraint is that the number of indexes in the constant
  // should be the same as the name array

  // initialize faculties.
  char *faculty_names[] = {
      "Faculty of Information Techonology",
      "Faculty of Law",
      "Faculty of Environment",
      "Faculty of Arts",
      "Faculty of Foreign Languages",
      "Faculty of Business Administration",
      "Faculty of Library-Office",
  };
  int number_of_faculties = sizeof(faculty_names) / sizeof(faculty_names[0]);
  faculty *faculties = init_faculties(faculty_names, number_of_faculties);

  // start the program by letting the user store the faculty members.
  printf("Program starting...\nPlease set up the program first.\n");
  for (int i = 0; i < number_of_faculties; i++) {
    int faculty_member_count = MINIMUM_COMMITTEE_MEMBER_COUNT;
    do {
      if (faculty_member_count > 0) {
        printf("Please input at least 3 committee member for %s, "
               "remaining: %d\n",
               faculty_names[i], faculty_member_count);
      }

      printf("'a': add a new committee member,'A': show current faculty "
             "members, 'n': next faculty, 'q': quit the program\n");
      char value = get_single_char("> ");

      switch (value) {
      case 'a': {
        unsigned int buffer_size = MAX_BUFFER_SIZE;
        committee_member *member = get_committee_member(buffer_size);
        add_member(member, &faculties[i]);
        print_committee_member(member);
        faculty_member_count--;
        break;
      }

      case 'A': {
        committee_member *member = faculties[i].members;
        // only print if the member list is not empty.
        if (member != NULL) {
          while (member != NULL) {
            print_committee_member(member);
            member = member->next_member;
          }
          printf("\n");
        }
        break;
      }

      case 'q': {
        printf("ending the program");
        goto end;
      }
      }
    } while (faculty_member_count > 0);
  }

  // start accepting the students and scheduling them
  while (true) {
    // menu
    printf(" ");
  }
  printf("number of faculties: %d", number_of_faculties);

end:
  printf("ending the program");
  free(faculties);
  return 0;
}
