package esiot.smart_bridge;

public class Sample {

	private long ts;
	private double value;
	
	public Sample(long ts, double value) {
		this.ts = ts;
		this.value = value;
	}
	
	public long getTimestamp() {
		return ts;
	}
	
	public double getValue() {
		return value;
	}
}
