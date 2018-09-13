for ((i=0;i<1;i++)); do
	cd src/build
	./fann_mushroom
	cd -
	cd bellerophon
	./launch.sh >> log$i
	cd -
done

