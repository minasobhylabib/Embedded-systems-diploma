.section .vectors

.word	0x20001000	/* stack top address */
.word	_reset
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler
.word 	vector_handler

.section .text
_reset:
	bl main
	b .
.thumb_func
vector_handler:
	b _reset