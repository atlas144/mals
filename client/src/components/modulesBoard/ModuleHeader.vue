<template>
  <div>
    <h1>{{ name }}</h1>
    <hr />
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";

@Options({
  props: {
    name: {
      type: String,
      required: false,
      default: 'Unknown module',
    },
  },
})
export default class ModuleHeader extends Vue {
  public name!: string;
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
