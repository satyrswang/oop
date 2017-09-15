public class WordCount  {
	public static class Map extends Mapper<LongWritable,Text,Text,IntWriter>{
		private final static IntWriter one = new IntWriter(1);
		private Text word = new Text();

		public void map(LongWritable key,Text value,Context context) throws IOException , InterruptedException{
			String line = value.toString();
			StringTokenizer tokenizer = new StringTokenizer(line);
			while(tokenizer.hasMoreTokens()){
				word.set(tokenizer.nextToken());
				context.write(word,one);
			}
		}
	}

	public static class Reduce extends Reducer<Text ,IntWritable,Text,IntWritable>{
		
	}
}