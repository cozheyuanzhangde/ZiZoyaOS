void print_string(char* string) {
	char* video_memory = (char*) 0xb8000;
	char* strptr = string;
        while (*strptr != '\0'){
		*video_memory = *strptr;
		strptr++;
		video_memory = video_memory + 2;
        }
}

void main() {
	print_string("This message is for testing string printing.");
}
