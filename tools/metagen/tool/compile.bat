if not exist bin do mkdir bin
javac -cp ../js.jar;./src -d ./bin ./src/metagen.java
cd bin
jar cmf ../metagen.mf metagen.jar metagen.class com
mv metagen.jar ../../