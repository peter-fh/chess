#include "pst_manager.h"

int main() {
	PstManager pst_manager;
	pst_manager.generate_psts();
	pst_manager.write_psts();
}
