#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_OF_DAYS 5
#define MAX_NUMBER_OF_TIME_INDEX 18
#define MAX_BUFFER_SIZE 100

typedef struct {
  int hour;
  int minutes;
} time_exp;

// committee_member defines a committee member that will
// audit the student's research
// this is to create a singly linked list.
typedef struct committee_member {
  char *name;           // name of the committee_member
  char *degree;         // name of the degree(PhD or Master,etc.)
  char *title;          // academic title of the committee_member
  time_exp *start_time; // available since this start time of a day
  time_exp *stop_time;  // unavailable start from this time of a day
  struct committee_member *next_member; // pointer to the next committee_member
} committee_member;

// meeting defines the time that a commitee member and a student will meet
// for research auditioning
typedef struct {
  char *student_name; // name of the student who's making the research
  int expected_day;   // expected time of the meeting as index(8am to 5pm)
  int expected_time;  // expected day of the meeting as index(mon-fri)
  committee_member *authority; // pointer to a committee_member;
} meeting;

// time_available defines the times that a meeting can be made or not
// if the unavailable is false then a meeting can be made in that time.
typedef struct {
  bool unavailable; // meeting is available or not for that time period
  meeting *meeting; // pointer to a meeting.
} time_available;

// faculty is a faculty of the university
typedef struct {
  // name of the faculty
  char *faculty_name;

  // array of the times that a meeting can take place.
  // availablity is from monday-friday, from 8am-5pm;
  time_available time_array[MAX_NUMBER_OF_DAYS][MAX_NUMBER_OF_TIME_INDEX];

  // the last day of the scheduled meeting of a week.
  int last_day_index;

  // the last time of the scheduled meeting of a day.
  int last_time_index;

  // array/tree of meetings that is sorted every time a meeting is added.
  meeting *meetings;

  // array/linked_list of committee members that doesn't need to be sorted
  // but it's very good if we can sort it by their available times.
  committee_member *members;

  // number of the members in this faculty.
  int member_count;
} faculty;

faculty *init_faculties(char *faculty_names[], int number_of_faculties);

committee_member *get_committee_member(unsigned int buffer_size);

void print_committee_member(committee_member *member);

char get_single_char(const char *prompt);

char *get_string(const char *prompt, unsigned int buffer_size);

time_exp *get_time(const char *prompt);

void add_member(committee_member *member, faculty *faculty);
