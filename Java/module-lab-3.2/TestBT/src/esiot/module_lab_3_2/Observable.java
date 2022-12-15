package esiot.module_lab_3_2;

import java.util.LinkedList;

public class Observable {
	
	private LinkedList<Observer> observers;
	
	protected Observable(){
		observers = new LinkedList<Observer>();
	}
	
	protected void notifyEvent(Event ev){
		synchronized (observers){
			for (Observer obs: observers){
				obs.notifyEvent(ev);
			}
		}
	}

	public void addObserver(Observer obs){
		synchronized (observers){
			observers.add(obs);
		}
	}

	public void removeObserver(Observer obs){
		synchronized (observers){
			observers.remove(obs);
		}
	}

}
