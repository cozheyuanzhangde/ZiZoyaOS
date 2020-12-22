void main() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'B';   //store the char at the address pointed by the video_memory.
}
