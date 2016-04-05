ROOMACTIONS = RoomAction.java BFRoomAction.java FeastRoomAction.java CoinRoomAction.java EmptyRoomAction.java GrueRoomAction.java TreasureRoomAction.java FactorialRoomAction.java HuntRoomAction.java ExitRoomAction.java JokeRoomAction.java

SRC = $(ROOMACTIONS) Room.java GrueHunt.java InGenerate.java

joosc: $(SRC) clean
	$(PEEPDIR)/joosc $(SRC)

joosco: $(SRC) clean
	$(PEEPDIR)/joosc -O $(SRC)

GrueHunt: $(SRC)
	javac -cp $(PEEPDIR)/jooslib.jar: $(SRC)

gen:
	javac -cp $(PEEPDIR)/jooslib.jar: InGenerate.java
	java -cp $(PEEPDIR)/jooslib.jar: InGenerate > in1

clean:
	rm -f *.class *.j *.optdump *.dump

