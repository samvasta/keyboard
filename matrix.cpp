// 
// Turns on one row at a time and reads cols in each row
// 

#include "matrix.h"
#include "common.h"
#include "core_pins.h"
#include "keyhandler.h"

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static void init_cols(void);
static bool read_cols_on_row(matrix_row_t[], uint8_t);
static void unselect_rows(void);
static void select_row(uint8_t);
static void unselect_row(uint8_t);


static uint16_t debouncing_time;
static bool debouncing = false;

static uint32_t time_elapsed(uint32_t last) {
	return millis() - last;
}


void setup_matrix() {
	initMatrix();
	unselect_rows();
	init_cols();

	// initialize matrix state: all keys off
	for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
		matrix[i] = 0;
		matrix_debouncing[i] = 0;
	}
}

void scan_matrix() {
	// Set row, read cols
	for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
		bool matrix_changed = read_cols_on_row(matrix_debouncing, current_row);

		if (matrix_changed) {
			debouncing = true;
			debouncing_time = millis();
		}
	}
	if (debouncing && (time_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
		for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
			matrix[i] = matrix_debouncing[i];
		}
		debouncing = false;
	}

	processMatrixState(matrix);
}

void init_cols(void)
{
	for (uint8_t x = 0; x < MATRIX_COLS; x++) {
		setPinInputHigh(col_pins[x]);
	}
}


bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
	// Store last value of row prior to reading
	matrix_row_t last_row_value = current_matrix[current_row];

	// Clear data in matrix row
	current_matrix[current_row] = 0;

	// Select row and wait for row selecton to stabilize
	select_row(current_row);
	wait_us(30);

	// For each row...
	for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

		// Select the col pin to read (active low)
		uint8_t pin_state = readPin(col_pins[col_index]);

		// Populate the matrix col with the state of the row pin
		current_matrix[current_row] |= pin_state ? 0 : (1 << col_index);
	}

	// Unselect row
	unselect_row(current_row);

	return (last_row_value != current_matrix[current_row]);
}

//Set row to mode = OUTPUT (Low)
void select_row(uint8_t row)
{
	setPinOutput(row_pins[row]);
	writePinLow(row_pins[row]);
}

//Set row to mode = INPUT (Pullup)
void unselect_row(uint8_t row)
{
	setPinInputHigh(row_pins[row]);
}

void unselect_rows(void)
{
	for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
		setPinInput(row_pins[x]);
	}
}