## TCP Characteristics

|Characteristic|Description|
|---|---|
|[1. Relaible](Reliability) | Recovering lost packets, Achieved using seq numbers in header.|
|2. Connection Oriented |Send ACK after data transfer, connection estbd and tear down.|
|3. Ordered data |Data reaches intended destination in the same order it was sent.|
|4. Error Detection|Selective ACK(SACK)|
|5. Error Checking|Checksum|
|6. Recovering lost packet|[Using TCP IR Option](Lost_Packet_Recovery)|
|7. [Flow control](Flow_Control)| Sliding window|
|8. [Congestion Control](Flow_Control)|Provisioning, Traffic Aware routing, admission control, nagle algo, tcp delayed ack|
|9. Quality of service||
|10. Full duplex server|it can perform roles of both receiver and sender|
|11.Multiplexing|Using Port Numbers|
|12.Crash Recovery|Using SEQ Nos|
