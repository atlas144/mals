<template>
  <div>
    <label for="testInput">Test input</label>
    <input type="text" placeholder="Test input" name="testInput" id="testInput">
    <label for="testSelect">Test select</label>
    <select name="testSelect" id="testSelect">
      <option value="test1">Test 1</option>
      <option value="test2">Test 2</option>
      <option value="test3">Test 3</option>
      <option value="test4">Test 4</option>
    </select>
    <button id="testSubmit">Test submit</button>
  </div>
</template>

<script lang="ts">
import { Vue } from "vue-class-component";

export default class TestModule extends Vue {
  
}
</script>

<style scoped>
</style>
