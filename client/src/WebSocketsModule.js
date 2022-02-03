export default class WebSocketsModule {
  connection;
  callbacks;

  constructor(url, port) {
    this.connection = new WebSocket(
      `wss://${url}${port === undefined ? "" : `:${port}`}`
    );
    this.callbacks = new Map();

    this.connection.onopen = (messageEvent) => {
      console.log(`WSS connection successfully opened. Event: ${messageEvent}`);
    };

    this.connection.onmessage = (messageEvent) => {
      const message = JSON.parse(messageEvent.data);
      const callback = this.callbacks.get(message.module);

      console.log(`Accepted message for ${message.module} module`);

      if (callback !== undefined) {
        callback(message.message);
      } else {
        console.error(`${message.module} has no callback`);
      }
    };

    this.connection.onerror = (messageEvent) => {
      console.log(`An error ocurred: ${messageEvent}`);
    };

    this.connection.onclose = (messageEvent) => {
      console.log(`WSS connection successfully closed. Event: ${messageEvent}`);
    };
  }

  registerCallback(
    moduleIdentifier,
    callback
  ) {
    this.callbacks.set(moduleIdentifier, callback);
    console.log(
      `Callback for module ${moduleIdentifier} successfully registered`
    );
  }

  sendMessage(moduleIdentifier, message) {
    this.connection.send(
      JSON.stringify({
        module: moduleIdentifier,
        message: message,
      })
    );
    console.log(`Message successfully sent to ${moduleIdentifier} module`);
  }

  isOpen() {
    return this.connection.readyState === 1;
  }
}
