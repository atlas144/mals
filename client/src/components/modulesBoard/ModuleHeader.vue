<template>
  <div>
    <h1>{{ name }}</h1>
    <hr />
  </div>
</template>

<script>
export default {
  props: {
    name: {
      type: String,
      required: false,
      default: "Unknown module",
    }
  }
}
</script>

<style scoped>
h1 {
  font-size: 24px;
  font-weight: bold;
  text-align: left;
}

hr {
  border: solid 2px #4e9f3d;
}
</style>
