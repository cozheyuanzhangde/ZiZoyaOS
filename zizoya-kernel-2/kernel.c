void test_function() {
}

void main() {
	char* video_memory = (char*) 0xb8000;
        *video_memory = 'B';   //store char X at the address pointed by the video_memory.
	test_function();
}
