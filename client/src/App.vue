<template>
  <div>
    <BoardHeader />
    <ModulesBoard />
  </div>
</template>

<script>
import BoardHeader from "./components/boardHeader/BoardHeader.vue";
import ModulesBoard from "./components/modulesBoard/ModulesBoard.vue";

export default {
  name: 'M.A.L.S. client',
  components: {
    BoardHeader,
    ModulesBoard,
  }
}
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
