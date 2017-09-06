import java.math.BigInteger;
import java.util.Scanner;

class uva10069 {
	
	public static void main(String[] args) {

		Scanner IN=new Scanner(System.in);
		int numberOfCase=IN.nextInt();
		String mainstr, pattern;

		while(numberOfCase-->0){
			mainstr=IN.next();
			pattern=IN.next();
			int size_mstr=mainstr.length();
			int size_patt=pattern.length();

			int sw=1;
			BigInteger table[][]=new BigInteger[2][size_mstr+1];
			for(int j=0;j<size_mstr;j++)
				table[0][j]=BigInteger.ONE;

			for(int i=0;i<size_patt;i++,sw=invertbool(sw)){
				table[sw][0]=BigInteger.ZERO;
				for(int j=0;j<size_mstr;j++){
					table[sw][j+1]=table[sw][j];
					if(pattern.charAt(i)==mainstr.charAt(j))
						table[sw][j+1]=table[sw][j+1].add(table[invertbool(sw)][j]);
				}
			}
			
			System.out.println(table[invertbool(sw)][size_mstr].toString());
		}
		IN.close();
	}
	
	static int invertbool(int i){
		return i==0 ? 1 : 0;
	}
	
}