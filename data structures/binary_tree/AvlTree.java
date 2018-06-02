import java.util.Queue;
import java.util.LinkedList;
import java.util.function.Consumer;

/*
1)Уточнить контракт между Node и клиентами и методами
2)Переписать без рекурсии
3)Написать АВЛ
4)итераторы
 */

class BinaryTree<T extends Comparable<T>>{
    private class Node<T>{
        //package-private
        T value = null;
        Node left = null;
        Node right = null;

        Node(){
        }
        Node(T value, Node left, Node right){
            this.value = value;
            this.left = left;
            this.right = right;
        }
    }
    private Node<T> root;

    private Node<T> addRecursive(Node<T> current, T value) {
        if (current == null) {
            return new Node<T>(value, null, null);
        }

        int compareResult = value.compareTo(current.value);
        if(compareResult < 0){
            current.left = addRecursive(current.left, value);
        } else if (compareResult > 0) {
            current.right = addRecursive(current.right, value);
        } else {
            // value already exists
        }

        return current;
    }

    public void add(T value){
        root = addRecursive(root, value);
    }

    private boolean containsNodeRecursive(Node<T> current, T value) {
        if (current == null) {
            return false;
        }
        if (value == current.value) {
            return true;
        }
        int compareResult = value.compareTo(current.value);
        return compareResult < 0
                ? containsNodeRecursive(current.left, value)
                : containsNodeRecursive(current.right, value);
    }

    public boolean containsNode(T value) {
        return containsNodeRecursive(root, value);
    }

    private T findSmallestValue(Node<T> subtreeRoot) {
        return subtreeRoot.left == null ? subtreeRoot.value : (T) findSmallestValue(subtreeRoot.left);
    }


    private Node<T> deleteRecursive(Node<T> current, T value) {
        if (current == null) {
            return null;
        }
        if(current.left == null && current.right == null)
            return null;//не имеет детей
        //имеется один ребенок
        if (current.right == null) {
            return current.left;
        }
        if (current.left == null) {
            return current.right;
        }
        //имеется два ребенка
        int compareResult = value.compareTo(current.value);
        if (compareResult == 0) {
            T smallestValue = (T) findSmallestValue(current.right);//наименьшее больше числа
            current.value = smallestValue;
            current.right = deleteRecursive(current.right, smallestValue);
            return current;
        }
        if (compareResult < 0) {
            current.left = deleteRecursive(current.left, value);
            return current;
        }
        current.right = deleteRecursive(current.right, value);
        return current;
    }

    public void remove(T value){
        root = deleteRecursive(root, value);
    }

    private void traverseInOrder(Node<T> node, Consumer<T> consumer) {
        if (node != null) {
            traverseInOrder(node.left, consumer);
            consumer.accept(node.value);
            traverseInOrder(node.right, consumer);
        }
    }

    private void traversePreOrder(Node<T> node, Consumer<T> consumer) {
        if (node != null) {
            consumer.accept(node.value);
            traversePreOrder(node.left, consumer);
            traversePreOrder(node.right, consumer);
        }
    }

    private void traversePostOrder(Node<T> node, Consumer<T> consumer) {
        if (node != null) {
            traversePostOrder(node.left, consumer);
            traversePostOrder(node.right, consumer);
            consumer.accept(node.value);
        }
    }

    private void traverseBreadthFirstOrder(Node<T> node, Consumer<T> consumer) {
        if (node == null) {
            return;
        }

        Queue<Node<T>> nodes = new LinkedList<>();
        nodes.add(node);

        while (!nodes.isEmpty()) {

            Node<T> currentNode = nodes.remove();

            consumer.accept(currentNode.value);

            if (currentNode.left != null) {
                nodes.add(currentNode.left);
            }

            if (currentNode.right!= null) {
                nodes.add(currentNode.right);
            }
        }
    }

    public void traverseInOrder(Consumer<T> consumer){
        traverseInOrder(root, consumer);
    }

    public void traversePreOrder(Consumer<T> consumer){
        traversePreOrder(root, consumer);
    }

    public void traversePostOrder(Consumer<T> consumer){
        traversePostOrder(root, consumer);
    }

    public void traverseBreadthFirstOrder(Consumer<T> consumer){
        traverseBreadthFirstOrder(root, consumer);
    }

}

public class AvlTree {

    public static void main(String[] args) {
        BinaryTree<Integer> bt = new BinaryTree<>();
        bt.add(3);
        bt.add(4);
        bt.add(1);

        bt.remove(3);
        bt.add(0);

        bt.traverseInOrder(System.out::println);
    }
}
