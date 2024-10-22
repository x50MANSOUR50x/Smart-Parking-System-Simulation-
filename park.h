#ifndef _park_h_
#define _park_h_
void start(void);
unsigned char track_spaces(void);
unsigned char calculate_fee(int *parking_duration);
void search_car(unsigned char id);
void display_status(void);
void reverse_entries(void);
#endif // _park_h_
