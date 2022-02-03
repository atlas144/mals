<template>
  <div>
    <label for="testInput">Test input</label>
    <input
      type="text"
      placeholder="Test input"
      name="testInput"
      id="testInput"
      v-model="testInputValue"
    />
    <label for="testSelect">Test select</label>
    <select name="testSelect" id="testSelect">
      <option value="test1">Test 1</option>
      <option value="test2">Test 2</option>
      <option value="test3">Test 3</option>
      <option value="test4">Test 4</option>
    </select>
    <label for="testValue">Test value</label>
    <span
      name="testValue"
      id="testValue"
    >{{ testValue }}</span>
    <button id="testSubmit" v-on:click="sendTestMessage">Test submit</button>
  </div>
</template>

<script>
import WebSocketsModule from "../../../../WebSocketsModule";

export default {
  props: {
    webSocketsModule: {
      type: WebSocketsModule,
      required: true,
    },
  },
  data() {
    return {
      moduleIdentifier: "TestModule",
      testInputValue: "",
      testValue: "-",
    }
  },
  methods: {
    onMessageCallback(message) {
      this.testValue = message.testValue;
    },
    sendTestMessage() {
      if (this.webSocketsModule.isOpen()) {
        this.webSocketsModule.sendMessage(this.moduleIdentifier, {
          testKey: this.testInputValue
        });
      }
    }
  },
  created() {
    if (this.webSocketsModule !== undefined) {
      this.webSocketsModule.registerCallback(
        this.moduleIdentifier,
        this.onMessageCallback
      );
    }
  }
}
</script>

<style scoped></style>
