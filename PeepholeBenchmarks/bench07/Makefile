ROOMACTIONS = RoomAction.java BFRoomAction.java FeastRoomAction.java CoinRoomAction.java EmptyRoomAction.java GrueRoomAction.java TreasureRoomAction.java FactorialRoomAction.java HuntRoomAction.java ExitRoomAction.java JokeRoomAction.java

SRC = $(ROOMACTIONS) Room.java GrueHunt.java InGenerate.java

GrueHunt: $(SRC)
	javac -cp $(PEEPDIR)/jooslib.jar: $(SRC)

joos: $(SRC)
	$(PEEPDIR)/joosc $(SRC)

gen:
	javac -cp $(PEEPDIR)/jooslib.jar: InGenerate.java
	java -cp $(PEEPDIR)/jooslib.jar: InGenerate > in1

clean:
	rm *.class *.j

