<template>
  <div>
    <BoardHeader />
    <ModulesBoard />
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import BoardHeader from "./components/boardHeader/BoardHeader.vue";
import ModulesBoard from "./components/modulesBoard/ModulesBoard.vue";

@Options({
  components: {
    BoardHeader,
    ModulesBoard,
  },
})
export default class App extends Vue { }
</script>

<style>
body {
  margin: 0;
  padding: 0;
  background-color: #191a19;
  font-family: Helvetica, Arial, sans-serif;
}

#app {
  font-family: OpenSauceTwoRegular;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: justify;
  color: #f5ffdb;
  margin: 0;
}
</style>