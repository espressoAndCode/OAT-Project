// RUN: %clang_cc1 -analyze -analyzer-checker=core -verify %s

// Zero-sized VLAs.
void check_zero_sized_VLA(int x) {
  if (x)
    return;

  int vla[x]; // expected-warning{{Declared variable-length array (VLA) has zero size}}
}

void check_uninit_sized_VLA() {
  int x;
  int vla[x]; // expected-warning{{Declared variable-length array (VLA) uses a garbage value as its size}}
}

// Negative VLAs.
static void vla_allocate_signed(int x) {
  int vla[x]; // expected-warning{{Declared variable-length array (VLA) has negative size}}
}

static void vla_allocate_unsigned(unsigned int x) {
  int vla[x]; // no-warning
}

void check_negative_sized_VLA_1() {
  vla_allocate_signed(-1);
}

void check_negative_sized_VLA_2() {
  vla_allocate_unsigned(-1);
}

void check_negative_sized_VLA_3() {
  int x = -1;
  int vla[x]; // expected-warning{{Declared variable-length array (VLA) has negative size}}
}

void check_negative_sized_VLA_4() {
  unsigned int x = -1;
  int vla[x]; // no-warning
}

void check_negative_sized_VLA_5() {
  signed char x = -1;
  int vla[x]; // expected-warning{{Declared variable-length array (VLA) has negative size}}
}

void check_negative_sized_VLA_6() {
  unsigned char x = -1;
  int vla[x]; // no-warning
}

void check_negative_sized_VLA_7() {
  signed char x = -1;
  int vla[x + 2]; // no-warning
}

void check_negative_sized_VLA_8() {
  signed char x = 1;
  int vla[x - 2]; // expected-warning{{Declared variable-length array (VLA) has negative size}}
}

void check_negative_sized_VLA_9() {
  int x = 1;
  int vla[x]; // no-warning
}

static void check_negative_sized_VLA_10_sub(int x)
{
  int vla[x]; // expected-warning{{Declared variable-length array (VLA) has negative size}}
}

void check_negative_sized_VLA_10(int x) {
  if (x < 0)
    check_negative_sized_VLA_10_sub(x);
}

static void check_negative_sized_VLA_11_sub(int x)
{
  int vla[x]; // no-warning
}

void check_negative_sized_VLA_11(int x) {
  if (x > 0)
    check_negative_sized_VLA_11_sub(x);
}
