fun main() {
  val allLines = generateSequence(::readLine).toList()
  val nums = allLines
    .dropLast(1)
    .map(String::trim)
    .map {
      it.split("""\s+""".toRegex()).map(String::toLong)
    }

  val ops = allLines.last().trim().split("""\s+""".toRegex())

  val total = (0..<nums[0].size)
    .map { i ->
      val op: (Long, Long) -> Long = if (ops[i] == "*") {
        Long::times
      } else {
        require(ops[i] == "+")
        Long::plus
      }
      nums.map{ it[i] }.reduce(op)
    }.sum()
  println(total)
}
