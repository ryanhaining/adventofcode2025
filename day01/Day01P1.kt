fun main() {
  println(
    generateSequence(::readLine)
    .map{ (if (it[0] == 'L') -1 else 1) * it.substring(1).toInt() }
    .runningFold(50, Int::plus)
    .count { it % 100 == 0 }
  )
}
