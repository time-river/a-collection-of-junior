class Employee {
    private String name;
    private int salary;
    public Employee(String name, int salary){
        this.name = name;
        this.salary = salary;
    }
    public String getDetails(){
        return "name: " + name + "\nSalary: " + salary;
    }
}

class Manager extends Employee{
    private String department;
    public Manager(String name, int salary, String department){
        super(name, salary);
        this.department = department;
    }
    public String getDetails(){
        return super.getDetails() + "\nDepartment: " + department;
    }
}

public class TestSuper{
    public static void main(String[] args){
        Manager m = new Manager("TOM", 2000, "Finance");
        System.out.println(m.getDetails());
    }
}
