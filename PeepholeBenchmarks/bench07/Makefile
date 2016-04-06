ROOMACTIONS = RoomAction.java BFRoomAction.java FeastRoomAction.java CoinRoomAction.java EmptyRoomAction.java GrueRoomAction.java TreasureRoomAction.java FactorialRoomAction.java HuntRoomAction.java ExitRoomAction.java JokeRoomAction.java

SRC = $(ROOMACTIONS) Room.java GrueHunt.java InGenerate.java

joosc: $(SRC) clean
	$(PEEPDIR)/joosc $(SRC)

joosco: $(SRC) clean
	$(PEEPDIR)/joosc -O $(SRC)

javac: $(SRC)
	javac -cp $(PEEPDIR)/jooslib.jar: $(SRC)

run:
	java -cp $(PEEPDIR)/jooslib.jar: GrueHunt < in1 >& gen1

clean:
	rm -f *.class *.j *.optdump *.dump
