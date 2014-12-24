public class HelloWorld4 {

    public static void main(String[] args) {
	System.out.println("Hello!");
        int number = Integer.parseInt(args[0]);
        if (number > 5)
        {
            System.out.println("Large number");
        }
        else
        {
            System.out.println("Small number");
        }
    }
}
