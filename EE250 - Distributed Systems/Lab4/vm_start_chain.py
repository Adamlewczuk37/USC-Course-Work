import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, rc):
    print("Connected to server (i.e., broker) with result code "+str(rc))

    client.subscribe("lewczuk/pong")
    
    client.message_callback_add("lewczuk/pong", on_message_from_ipinfo)

#Custom message callback.
def on_message_from_ipinfo(client, count, message):
   #replace user with your USC username in all subscriptions
    count = int(message.payload.decode())
    print("Ping")
    count = count + 1
    print(count)
    client.publish("lewczuk/ping", f"{count}")
    time.sleep(1)

if __name__ == '__main__':
    count = 0
    #get IP address
    ip_address="172.20.10.3"

    #create a client object
    client = mqtt.Client()
    
    #attach the on_connect() callback function defined above to the mqtt client
    client.on_connect = on_connect
    #attach a default callback which we defined above for incoming mqtt messages
    #client.on_message = on_message
   
    client.connect(host="172.20.10.3", port=1883, keepalive=60)

    client.publish("lewczuk/ping", f"{count}")

    client.loop_forever()