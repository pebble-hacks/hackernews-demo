function sendMessage() {
    Pebble.sendAppMessage({"title": "Top Hacker News Post"});
}

Pebble.addEventListener("ready",
    function(e) {
        console.log("Hello world! - Sent from your javascript application.");
    }
);

Pebble.addEventListener("appmessage",
    function(e) {
        console.log("Received message: " + e.payload.greeting);
        sendMessage();
    }
);
