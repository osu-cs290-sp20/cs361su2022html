make:
	gcc -std=c99 -o w workouts.c
	#gcc -std=c99 -o profile profile.c
	#gcc -std=c99 -o progress progrss.c

clean:
	rm -f w #profile progress
