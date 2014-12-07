all:
	lisaac mode.li -boost
	lisaac triangulate.li
	lisaac translate.li
	lisaac depth.li

mode:
	lisaac mode.li -boost

triangle:
	lisaac triangulate.li

translate:
	lisaac translate.li

depth:
	lisaac depth.li

clean:
	rm depth.c translate.c triangulate.c mode.c

clean_all:
	rm depth translate triangulate mode depth.c translate.c triangulate.c mode.c
