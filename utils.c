#include "utils.h"

const int OFFICE_START_HOUR = 8;
const int OFFICE_STOP_HOUR = 17;

// init_faculties initalizes the faculties with the given number of faculties.
faculty *init_faculties(char *faculty_names[], int number_of_faculties) {

  // allocate memory, you can use calloc if you want.
  faculty *faculties = malloc(sizeof(faculty) * number_of_faculties);
  if (faculties == NULL) {
    return NULL;
  }

  // initializing the memory that is allocated.
  for (int i = 0; i < number_of_faculties; i++) {
    faculties[i].faculty_name = faculty_names[i];
    faculties[i].last_day_index = 0;
    faculties[i].last_time_index = 0;
    faculties[i].meetings = NULL;
    for (int j = 0; j < MAX_NUMBER_OF_DAYS; j++) {
      for (int k = 0; k < MAX_NUMBER_OF_TIME_INDEX; k++) {
        faculties->time_array[i][j].unavailable = false;
        faculties->time_array[i][j].meeting = NULL;
      }
    }
  }

  return faculties;
}

// add_member adds the given member to the given faculty to form a linked list.
// also checks that the available times of the given member is overlapping with
// other or not.
void add_member(committee_member *member, faculty *faculty) {
  member->next_member = faculty->members;
  faculty->members = member;
  return;
}

committee_member *get_committee_member(unsigned int buffer_size) {
  committee_member *member = malloc(sizeof(committee_member));
  if (member == NULL) {
    exit(1); // memory issues.
  }

  // get the name
  member->name = malloc(sizeof(char) * buffer_size);
  if (member->name == NULL) {
    exit(1); // memory issues.
  }
  member->name = get_string("Name of committee member:\n", buffer_size);

  // get the degree
  member->degree = malloc(sizeof(char) * buffer_size);
  if (member->degree == NULL) {
    exit(1); // memory issues.
  }
  member->degree = get_string("Degree of committee member:\n", buffer_size);

  // get the title
  member->title = malloc(sizeof(char) * buffer_size);
  if (member->title == NULL) {
    exit(1); // memory issues.
  }
  member->title =
      get_string("Academic title of committee member:\n", buffer_size);

  // get the starting available time.
  member->start_time =
      get_time("Enter the starting available time in 24 hours format\n");
  member->stop_time =
      get_time("Enter the stop available time in 24 hours format\n");
  member->next_member = NULL; // Set next member to NULL
  return member;
}

// get_char gets a single character from the stdin.
// rejecting if there's more than one char and
// prompting the user to input only one char.
char get_single_char(const char *prompt) {
  char input;
  int extra_chars = 0;

  do {
    printf("%s", prompt);
    input = getchar();

    // clear the input buffer in case there are extra characters
    while (getchar() != '\n')
      extra_chars++;

    if (extra_chars > 0) {
      printf("Error: Please input exactly one character.\n");
      extra_chars = 0; // reset the extra_chars count
    }
  } while (input == '\n' ||
           input == EOF); // keep prompting if newline or EOF is entered

  return input;
}

// get_string gets a string from the stdin, returing an error if there's are
// any.
char *get_string(const char *prompt, unsigned int buffer_size) {
  char *buffer = malloc(sizeof(char) * buffer_size);
  while (true) {
    printf("%s", prompt);
    fgets(buffer, buffer_size, stdin);
    uint length = strlen(buffer);

    if (length >= buffer_size - 1 && buffer[length - 1] != '\n') {
      printf("Error: Exceeding the maximum number of characters.\n");
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
    } else {
      buffer[length - 1] = '\0';
      break;
    }
  }
  return buffer;
}

time_exp *get_time(const char *prompt) {
  int hours, minutes;
  int valid_input = false;
  time_exp *time = malloc(sizeof(time_exp));

  while (!valid_input) {
    // Prompt the user to input hours and minutes
    printf("%s", prompt);
    if (scanf("%d:%d", &hours, &minutes) != 2) {
      // If scanf doesn't read two integers due to invalid format
      printf("Invalid format. Please enter time in HH:MM of 24 hour format.\n");
      // Clear input buffer
      while (getchar() != '\n')
        ;
      continue;
    }

    // Check if the entered time is valid
    if (hours >= OFFICE_START_HOUR && hours <= OFFICE_STOP_HOUR &&
        minutes >= 0 && minutes < 60) {
      valid_input = true;
    } else {
      printf("Invalid time entered. Please enter a valid time.\n");
    }
  }
  time->hour = hours;
  time->minutes = minutes;
  return time;
}

void print_committee_member(committee_member *member) {
  printf("Member Information:\n\tName: %s,\n\tDegree: %s,\n\tTitle: "
         "%s,\n\tStart available: %02d:%02d,\n\tUnavailable: %02d:%02d\n",
         member->name, member->degree, member->title, member->start_time->hour,
         member->start_time->minutes, member->stop_time->hour,
         member->stop_time->minutes);
}
