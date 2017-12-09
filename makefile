myMovie : main.o choi_junsik.o lee_sanghyeon.o woo_hojin.o park_saejun.o
				gcc -o myMovie main.o choi_junsik.o lee_sanghyeon.o woo_hojin.o park_saejun.o
main.o : main.c movieProject.h
				gcc -c main.c
choi_junsik.o : choi_junsik.c movieProject.h
				gcc -c choi_junsik.c
lee_sanghyeon.o : lee_sanghyeon.c movieProject.h
				gcc -c lee_sanghyeon.c
woo_hojin.o : woo_hojin.c movieProject.h
				gcc -c woo_hojin.c
park_saejun.o : park_saejun.c movieProject.h
				gcc -c park_saejun.c
