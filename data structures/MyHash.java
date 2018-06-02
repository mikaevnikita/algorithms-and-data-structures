import java.util.*;

//метод длинных цепочек
class Hash<K, V>{
    private class HashEntry<K, V>{
        private K key;
        private V value;
        public HashEntry(K key, V value){
            this.key = key;
            this.value = value;
        }
        public K getKey(){
            return key;
        }
        public V getValue(){
            return value;
        }
        public void setKey(K key){
            this.key = key;
        }
        public void setValue(V value){
            this.value = value;
        }
        public boolean equals(Object o){
            if(o == null || o.getClass() != HashEntry.class)
                return false;
            HashEntry<K, V> obj = (HashEntry<K, V>) o;
            return this.key.equals(obj.key);//сравнение по ключу
        }
    }
    private int capacity = 10;
    private int elementsCount = 0;
    private final double loadFactorForRealloc = 0.6;
    private final int reallocCoefficient = 2;
    private ArrayList<HashEntry<K, V>>[] table = new ArrayList[capacity];

    private double getLoadFactor(){
        return elementsCount / capacity;
    }

    private boolean insertInto(ArrayList<HashEntry<K, V>>[] table, int indexForInsert, HashEntry<K, V> entry){
        if(table[indexForInsert] == null)
            table[indexForInsert] = new ArrayList<>();
        ArrayList<HashEntry<K, V>> chain = table[indexForInsert];

        boolean added = false;

        int indexOfTableFindedEntry = chain.indexOf(entry);//find by key
        if(indexOfTableFindedEntry < 0) {
            chain.add(entry);
            added = true;
        }
        else
            chain.get(indexOfTableFindedEntry).setValue(entry.getValue());//update value
        return added;
    }

    //возращает индекс
    private int getReflectionOfHash(Object o, int tableSize){
        return Math.abs(o.hashCode() % tableSize);
    }

    private void realloc(){
        int newCapacity = capacity * reallocCoefficient;
        ArrayList<HashEntry<K, V>>[] newTable = new ArrayList[newCapacity];

        for (int i = 0; i < table.length ; i++) {
            ArrayList<HashEntry<K, V>> currentChain = table[i];
            if(currentChain == null)
                continue;

            for (int j = 0; j < currentChain.size(); j++) {
                HashEntry<K, V> currentEntry = currentChain.get(j);
                K key = currentEntry.getKey();
                int newIndexAfterRealloc = getReflectionOfHash(key, newCapacity);
                insertInto(newTable, newIndexAfterRealloc, currentEntry);
            }
        }

        table = newTable;
        capacity = newCapacity;
    }

    public void put(K key, V value){
        double loadFactor = getLoadFactor();
        if(loadFactor >= loadFactorForRealloc)
            realloc();

        int index = getReflectionOfHash(key, table.length);
        HashEntry<K, V> currentEntry = new HashEntry<>(key, value);

        boolean addedNewValue = insertInto(this.table, index, currentEntry);
        if(addedNewValue)
            elementsCount++;

    }

    public V get(K key) throws NoSuchElementException{
        int index = getReflectionOfHash(key, table.length);
        V value = null;
        if(!(table[index] == null)){
            HashEntry<K, V> currentEntry = new HashEntry<>(key, value);
            int findedIndex = table[index].indexOf(currentEntry);
            if(findedIndex >= 0)
                value = table[index].get(findedIndex).getValue();
        }
        if(value == null)
            throw new NoSuchElementException();
        return value;

    }

    public int size(){
        return elementsCount;
    }
}

public class MyHash
{

    public static void main(String[] args)
    {
        Hash<String, Integer> hash = new Hash<>();

        for (int i = 0; i < 100; i++) {
            hash.put(Integer.toString(i), i);
        }
        for(int i = 0; i < 100; i++)
            System.out.println(hash.get(Integer.toString(i)));
    }
}
