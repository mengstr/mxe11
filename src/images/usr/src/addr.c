main() {
  int a;
  printf("main address: %x (0%o)\n", main, main);
  printf("stack address: %x (0%o)\n", &a, &a);
  printf("heap address: %x (0%o)\n", sbrk(0), sbrk(0));
}
