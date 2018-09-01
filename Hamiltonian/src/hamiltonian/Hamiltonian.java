package hamiltonian;
import java.util.Scanner;
import java.util.Arrays;
public class Hamiltonian {
    int V;
    int[][] graph;
    int[] path ;
     int pathcount;
    void hamiltonian(int[][] g){
        graph=g;
       V=g.length;
       path=new int[V];
        
        Arrays.fill(path,-1);
        try {
            path[0]=0;pathcount=1;
            solve(0);
                    System.out.println( "no sol"); 
        }catch(Exception ex){
             System.out.println(ex.getMessage());
             display();
        }
    }
    void solve (int vertex) throws Exception{
        if(graph[vertex][0]==1 && pathcount==V){
            throw new  Exception("Sol found");
        }
            if(pathcount==V){
                return;
            }
            for(int v=0;v<V ;v++){
               
                if (graph[vertex][v]==1){
                    path[pathcount++]=v;
                    graph[vertex][v]=0;
                    graph[v][vertex]=0;
                    if(!ispresent(v)){
                        solve(v);
                    }
                    graph[vertex][v]=1;
                    graph[v][vertex]=1;
                    path[--pathcount]=-1;
                }
            }
        }
    
        boolean ispresent(int v){
        for(int i=0;i<pathcount-1;i++){
            if(path[i]==v)           
            return true;
            
        }
        return false;
        }
    
    
      void display(){
        for(int i=0;i<=V;i++)
            System.out.print(path[i%V] +" ");
            System.out.println();
        
    
}
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Hamiltonian hc=new Hamiltonian();
 int V=sc.nextInt();
 int[][] graph=new int[V][V];
 for(int i=0;i<V;i++){
     for(int j=0;j<V;j++){
         graph[i][j]=sc.nextInt();
     }
 }
 hc.hamiltonian(graph);
    }
    
}
