FLUTTER = flutter

app:
	cd app/; \
	$(FLUTTER) run

clean:
	cd app/; $(FLUTTER) clean; rm -rf build/
	rm -f *.o
