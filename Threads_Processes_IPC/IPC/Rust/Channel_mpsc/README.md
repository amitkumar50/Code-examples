- [Channel](#ch)
- [1 producer 1 consumer](#1p1c)

<a name=ch></a>
## Channel
- Channel is similar to [Pipe in Linux](/Threads_Processes_IPC/IPC).
- It has two halves: a transmitter and a receiver. The transmitter(sender) put rubber ducks into the river, and the receiver gets the duck.
- One part of your code calls methods on the transmitter with the data you want to send, and another part checks the receiving end for arriving messages.
- A channel is said to be closed if either the transmitter or receiver half is dropped.
- **mpsc: multiple producer single consumer**

<a name=1p1c></a>
## 1 Producer, 1 consumer
```rs
use std::sync::mpsc;                            //mpsc: Multiple producer, Single Consumer.
use std::thread;


fn main() {
    let (tx, rx) = mpsc::channel();            //1. Created channel having 2 ends(transmitter, reciever)
    
    let tid1 = thread::spawn(                  //2. Thread-1(Transmitter) owns tx(using move) and sends val=test on it
        move || {
            let val = String::from("test");
            tx.send(val).unwrap();
            //println!("{}", val);              //We cannot use value after sending over channel, bcoz reciever might change it.
        }                                       //ie ownership is transferred.
    );
    
    println!("{}", rx.recv().unwrap());         //3. Thread-2(main) recieves message over rx end of channel.
}
$ cargo run
test
```

<a name=mp1c></a>
## Multiple Producer 1 consumer
We will clone transmitting end of channel.
```rs
use std::sync::mpsc;
use std::thread;
use std::time::Duration;

fn main() {
    let (tx, rx) = mpsc::channel();
    let tx1 = tx.clone();
    
    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("thread1"),
        ];
        for val in vals {
            tx1.send(val).unwrap();                 //Sending over tx1
            thread::sleep(Duration::from_secs(1));
        }
    });

    thread::spawn(move || {
        let vals = vec![
            String::from("more"),
            String::from("messages"),               
        ];

        for val in vals {
            tx.send(val).unwrap();                    //Sending over tx
            thread::sleep(Duration::from_secs(1));
        }
    });

    for i in rx {
        println!("{}", i);
    }
}
$ cargo run
hi more thread1 from messages                       //See threads are executed in different order hence values recieved in different order
```
